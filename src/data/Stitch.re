type tClient;
type tService;
type tDb;
type tCollection;
type tQuery;
type tObjectId;

module Client = {
  [@bs.module "mongodb-stitch"] [@bs.scope "StitchClientFactory"]
  external create: string => Js.Promise.t(tClient) = "";

  [@bs.module "mongodb-stitch"] [@bs.scope "BSON"]
  external createObjectId: string => tObjectId = "ObjectId";

  [@bs.send] external login: tClient => Js.Promise.t(unit) = "";
  [@bs.send] external authedId: tClient => string = "";
  [@bs.send] external service: (tClient, string, string) => tService = "";

  [@bs.send] external db: (tService, string) => tDb = "";
  [@bs.send] external collection: (tDb, string) => tCollection = "";
};

module Collection = {
  [@bs.send] external find: (tCollection, 'findQuery) => tQuery = "";
  [@bs.send]
  external updateOne:
    (tCollection, 'findQuery, 'updateQuery, 'options) =>
    Js.Promise.t(Js.Json.t) =
    "";
  [@bs.send]
  external deleteOne:
    (tCollection, 'filter) => Js.Promise.t({. deletedCount: int}) =
    "";
  [@bs.send]
  external insertOne:
    (tCollection, 'document) => Js.Promise.t({. insertedId: int}) =
    "";
};

module Query = {
  [@bs.send] external execute: tQuery => Js.Promise.t(Js.Json.t) = "";
};

[@bs.send] external toString: Js.Json.t => string = "";

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