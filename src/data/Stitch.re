type stitchDb;
type collection;
type query;

module Client = {
  type stitchClient;
  type stitchService;

  [@bs.module "mongodb-stitch"] [@bs.scope "StitchClientFactory"]
  external create : string => Js.Promise.t(stitchClient) = "";

  [@bs.send] external login : stitchClient => Js.Promise.t(unit) = "";
  [@bs.send] external authedId : stitchClient => string = "";
  [@bs.send]
  external service : (stitchClient, string, string) => stitchService = "";

  [@bs.send] external db : (stitchService, string) => stitchDb = "";
  [@bs.send] external collection : (stitchDb, string) => collection = "";
};

module Collection = {
  [@bs.send] external find : (collection, 'findQuery) => query = "";
  [@bs.send]
  external updateOne :
    (collection, 'findQuery, 'updateQuery, 'options) =>
    Js.Promise.t(Js.Json.t) =
    "";
};

module Query = {
  [@bs.send] external execute : query => Js.Promise.t(Js.Json.t) = "";
};