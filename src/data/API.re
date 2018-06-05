let stitchClient: ref(option(Stitch.tClient)) = ref(None);
let stitchDb: ref(option(Stitch.tDb)) = ref(None);

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

module Job = {
  let getAll = callback => {
    let client = getClient();
    let db = getDb();

    let owner_id = Stitch.Client.authedId(client);
    let query = findQuery(~owner_id, ());

    /* Stitch.(
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
       ); */

    Stitch.(
      Client.collection(db, "jobs")
      |. Collection.find(query)
      |. Query.execute
      |> Js.Promise.then_(result => {
           %raw
           {| window.result = result|};
           callback(result |> JobData.Decode.jobs);

           Js.Promise.resolve();
         })
      |> ignore
    );
  };

  let delete = (~id: string, ~callback) => {
    let client = getClient();
    let db = getDb();

    let owner_id = Stitch.Client.authedId(client);

    Stitch.(
      Client.collection(db, "jobs")
      |. Collection.deleteOne({"owner_id": owner_id, "id": id})
    );
  };

  let create = (~job: JobData.job) => {
    let client = getClient();
    let db = getDb();

    let owner_id = Stitch.Client.authedId(client);

    let data = job |> JobData.Encode.job;

    Stitch.(Client.collection(db, "jobs") |. Collection.insertOne(data));
  };
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