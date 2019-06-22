[@react.component]
let make = _ => {
  let (path, setPath) =
    React.useState(_ => ReasonReact.Router.dangerouslyGetInitialUrl().path);

  React.useEffect0(_ => {
    let watcherID = ReasonReact.Router.watchUrl(url => setPath(_ => url.path));
    ();
    Some(() => ReasonReact.Router.unwatchUrl(watcherID));
  });

  <div>
    <Header />
    {switch (path) {
     | ["job", "post"] => <CreateJobPage />
     | ["account"] => <AccountPage />
     | _ => <HomePage />
     }}
  </div>;
};