let stitchClient: ref(option(Stitch.tClient)) = ref(None);
let stitchDb: ref(option(Stitch.tDb)) = ref(None);

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
    let db = getDb();

    Stitch.(
      Client.collection(db, "jobs")
      |. Collection.find(Js.Obj.empty)
      |. Query.execute
      |> Js.Promise.then_(result => {
           callback(result |> JobData.Decode.jobs);

           Js.Promise.resolve();
         })
      |> ignore
    );
  };

  let delete = (~id: string, ~callback) => {
    let db = getDb();

    Stitch.(
      Client.collection(db, "jobs")
      |. Collection.deleteOne({"_id": Stitch.Client.createObjectId(id)})
      |> Js.Promise.then_(val_ => Js.Promise.resolve(callback(val_)))
    );
  };

  let create = (~job: JobData.job) => {
    let db = getDb();

    let data = job |> JobData.Encode.job;

    Stitch.(Client.collection(db, "jobs") |. Collection.insertOne(data));
  };

  let update = (~id: string) => {
    let db = getDb();

    Stitch.(
      Client.collection(db, "jobs")
      |. Collection.updateOne(
           {"_id": Stitch.Client.createObjectId(id)},
           {
             "$set": {
               "number": 44,
             },
           },
           {"upsert": true},
         )
      |> ignore
    );
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