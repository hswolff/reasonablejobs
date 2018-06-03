open Stitch;

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

let fetchJobs = (client, db) => {
  let owner_id = Client.authedId(client);
  let query = findQuery(~owner_id, ());

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
  |> ignore;

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
     });
};

let createStitchClient = () =>
  Client.(
    create("reasonablejobs-kitjl")
    |> Js.Promise.then_(client => {
         Js.log("ok");
         Js.log(client);
         let db =
           client |. service("mongodb", "mongodb-atlas") |. db("data");
         Js.log(db);
         %raw
         {| window.client = client|};
         %raw
         {| window.db = db|};
         client
         |> login
         |> Js.Promise.then_(() => Js.Promise.resolve((client, db)));
       })
    |> Js.Promise.then_(((client, db)) => {
         fetchJobs(client, db);
         Js.Promise.resolve();
       })
  );

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