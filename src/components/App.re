type state = {path: list(string)};

type action =
  | Route(list(string));

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    path: ReasonReact.Router.dangerouslyGetInitialUrl().path,
  },
  reducer: (action, _state) =>
    switch (action) {
    | Route(path) => ReasonReact.Update({path: path})
    },
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url => self.send(Route(url.path)));
    ();
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self =>
    <div>
      <Header />
      {switch (self.state.path) {
       | ["job", "post"] => <CreateJobPage />
       | ["account"] => <AccountPage />
       | _ => <HomePage />
       }}
    </div>,
};