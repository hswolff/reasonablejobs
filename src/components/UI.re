[@bs.config {jsx: 3}];

module Content3 = {
  let container =
    Css.(
      style([
        margin2(~v=px(0), ~h=auto),
        width(px(Config.Styles.contentWidth)),
      ])
    );

  [@react.component]
  let make = (~tagName="div", ~className="", ~children) => {
    ReactDOMRe.createDOMElementVariadic(
      tagName,
      ~props=ReactDOMRe.domProps(~className, ()),
      [|children|],
    );
  };
};

module Content = {
  let component = ReasonReact.statelessComponent("Image");
  /* `children` is not labelled, as it is a regular parameter in version 2 of JSX */
  let make = (~tagName="div", ~className="", children) =>
    ReasonReactCompat.wrapReactForReasonReact(
      Content3.make,
      Content3.makeProps(~tagName, ~className, ~children=React.null, ()),
      children,
    );
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
        ReactDOMRe.createElementVariadic(
          asTag,
          ~props=
            ReactDOMRe.objToDOMProps({
              "href": href,
              "className": self.state.active ? activeClassName : className,
              "onClick": e => {
                ReactEvent.Mouse.preventDefault(e);
                ReasonReact.Router.push(href);
              },
            }),
          children,
        ),
    };
  };
};