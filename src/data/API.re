let stitchClient: ref(option(Stitch.tClient)) = ref(None);
let stitchDb: ref(option(Stitch.tDb)) = ref(None);

module Decode = {
  let job = json : JobData.test =>
    Json.Decode.{
      number: json |> field("number", int),
      owner_id: json |> field("owner_id", string),
    };

  let jobs = json => json |> Json.Decode.list(job);
};

[@bs.deriving abstract]
type findQuery = {
  [@bs.optional]
  name: string,
  owner_id: string,
};

let fetchJobs = () => {
  let client =
    switch (stitchClient^) {
    | Some(c) => c
    | None => assert(false)
    };
  let db =
    switch (stitchDb^) {
    | Some(c) => c
    | None => assert(false)
    };

  let owner_id = Stitch.Client.authedId(client);
  let query = findQuery(~owner_id, ());

  Stitch.(
    Client.collection(db, "jobs")
    |. Collection.updateOne(
         {"owner_id": owner_id},
         {
           "$set": {
             "number": 44,
           },
         },
         {"upsert": true},
       )
    |> ignore
  );

  Stitch.(
    Client.collection(db, "jobs")
    |. Collection.find(query)
    |. Query.execute
    |> Js.Promise.then_(result => {
         Js.log2("hi", result);

         let line = result |> Decode.jobs;
         switch (line) {
         | [val_] => Js.log2("eh??", val_.number)
         | _ => Js.log("Empty")
         };
         Js.Promise.resolve();
       })
  );
};

let createStitchClient = done_ =>
  Stitch.Client.create("reasonablejobs-kitjl")
  |> Js.Promise.then_(client => {
       Js.log2("StitchClient", client);
       stitchClient := Some(client);

       let db =
         Stitch.Client.(
           client |. service("mongodb", "mongodb-atlas") |. db("data")
         );

       stitchClient := Some(client);
       stitchDb := Some(db);

       %raw
       {| window.client = client|};
       %raw
       {| window.db = db|};

       client |> Stitch.Client.login;
     })
  |> Js.Promise.then_(() => {
       done_();
       Js.Promise.resolve();
     });

%raw
{|
/**
const stitch = require('mongodb-stitch');
window.stitch = stitch;
const clientPromise = stitch.StitchClientFactory.create('reasonablejobs-kitjl');
clientPromise.then(client => {
  const db = client.service('mongodb', 'mongodb-atlas').db('data');
  client.login().then(() =>
    db.collection('jobs').updateOne({owner_id: client.authedId()}, {$set:{number:42}}, {upsert:true})
  ).then(() =>
    db.collection('jobs').find({owner_id: client.authedId()}).limit(100).execute()
  ).then(docs => {
    console.log("Found docs", docs)
    console.log("[MongoDB Stitch] Connected to Stitch")
  }).catch(err => {
    console.error(err)
  });
});
**/
|};