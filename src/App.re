type state = {path: list(string)};

type action =
  | Route(list(string));

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    path: ReasonReact.Router.dangerouslyGetInitialUrl().path,
  },
  reducer: (action, state) =>
    switch (action) {
    | Route(path) => ReasonReact.Update({path: path})
    },
  didMount: self => {
    Js.log("Hello");
    let watcherID =
      ReasonReact.Router.watchUrl(url => {
        Js.log(url.path);
        self.send(Route(url.path));
      });
    ();
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self =>
    <div>
      <Header />
      <UI.Content>
        <span> (ReasonReact.string("Content")) </span>
      </UI.Content>
      (
        switch (self.state.path) {
        | ["about"] => <h1> (ReasonReact.string("About Page")) </h1>
        | _ => <HomePage />
        }
      )
    </div>,
};