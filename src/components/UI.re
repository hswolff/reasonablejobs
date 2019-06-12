module Content = {
  let container =
    Css.(
      style([
        margin2(~v=px(0), ~h=auto),
        width(px(Config.Styles.contentWidth)),
      ])
    );

  let component = ReasonReact.statelessComponent("Content");

  let make =
      (
        ~tagName="div",
        ~className="",
        children: array(ReasonReact.reactElement),
      ) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        tagName,
        ~props={"className": String.concat(" ", [container, className])},
        children,
      ),
  };
};

module Link = {
  type state = {active: bool};
  type action =
    | Active
    | InActive;

  let component = ReasonReact.reducerComponent("Link");

  let getPath = (routerPath: list(string)) =>
    switch (routerPath) {
    | [] => "/"
    | pathList => "/" ++ String.concat("/", pathList)
    };

  let make =
      (~asTag="a", ~href, ~className="", ~activeClassName="active", children) => {
    let isActive = path => getPath(path) == href;

    {
      ...component,
      initialState: () => {
        active: isActive(ReasonReact.Router.dangerouslyGetInitialUrl().path),
      },
      reducer: (action, _state) =>
        switch (action) {
        | Active => ReasonReact.Update({active: true})
        | InActive => ReasonReact.Update({active: false})
        },
      didMount: self => {
        let watcherID =
          ReasonReact.Router.watchUrl(url =>
            self.send(isActive(url.path) ? Active : InActive)
          );
        ();
        self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
      },
      render: self =>
        ReasonReact.createDomElement(
          asTag,
          ~props={
            "href": href,
            "className": self.state.active ? activeClassName : className,
            "onClick": e => {
              e->ReactEvent.Mouse.preventDefault;
              ReasonReact.Router.push(href);
            },
          },
          children,
        ),
    };
  };
};