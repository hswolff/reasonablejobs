let stitchClient: ref(option(Stitch.tClient)) = ref(None);
let stitchDb: ref(option(Stitch.tDb)) = ref(None);

module Decode = {
  let job = json : JobData.test =>
    Json.Decode.{
      number: json |> field("number", int),
      owner_id: json |> field("owner_id", string),
    };

  let jobs = json => json |> Json.Decode.array(job);
};

[@bs.deriving abstract]
type findQuery = {
  [@bs.optional]
  name: string,
  owner_id: string,
};

let getClient = () =>
  switch (stitchClient^) {
  | Some(c) => c
  | None => assert(false)
  };

let getDb = () =>
  switch (stitchDb^) {
  | Some(c) => c
  | None => assert(false)
  };

let fetchJobs = callback => {
  let client = getClient();
  let db = getDb();

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
         callback(result |> Decode.jobs);

         Js.Promise.resolve();
       })
    |> ignore
  );
};

let createStitchClient = done_ =>
  Stitch.Client.create("reasonablejobs-kitjl")
  |> Js.Promise.then_(client => {
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