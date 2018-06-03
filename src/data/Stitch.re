type tClient;
type tService;
type tDb;
type tCollection;
type tQuery;

module Client = {
  [@bs.module "mongodb-stitch"] [@bs.scope "StitchClientFactory"]
  external create : string => Js.Promise.t(tClient) = "";

  [@bs.send] external login : tClient => Js.Promise.t(unit) = "";
  [@bs.send] external authedId : tClient => string = "";
  [@bs.send] external service : (tClient, string, string) => tService = "";

  [@bs.send] external db : (tService, string) => tDb = "";
  [@bs.send] external collection : (tDb, string) => tCollection = "";
};

module Collection = {
  [@bs.send] external find : (tCollection, 'findQuery) => tQuery = "";
  [@bs.send]
  external updateOne :
    (tCollection, 'findQuery, 'updateQuery, 'options) =>
    Js.Promise.t(Js.Json.t) =
    "";
};

module Query = {
  [@bs.send] external execute : tQuery => Js.Promise.t(Js.Json.t) = "";
};