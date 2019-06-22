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
  let make = (~tagName="div", ~className="", children) =>
    ReasonReactCompat.wrapReactForReasonReact(
      Content3.make,
      Content3.makeProps(~tagName, ~className, ~children=React.null, ()),
      children,
    );
};

module Link3 = {
  let getPath = (routerPath: list(string)) =>
    switch (routerPath) {
    | [] => "/"
    | pathList => "/" ++ String.concat("/", pathList)
    };

  [@react.component]
  let make =
      (~asTag="a", ~href, ~className="", ~activeClassName="active", ~children) => {
    let isActive = path => getPath(path) == href;

    let (active, setActive) =
      React.useState(_ =>
        isActive(ReasonReact.Router.dangerouslyGetInitialUrl().path)
      );

    React.useEffect0(_ => {
      let watcherID =
        ReasonReact.Router.watchUrl(url =>
          setActive(_ => isActive(url.path) ? true : false)
        );
      ();
      Some(() => ReasonReact.Router.unwatchUrl(watcherID));
    });

    let onClick = e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(href);
    };

    ReactDOMRe.createDOMElementVariadic(
      asTag,
      ~props=
        ReactDOMRe.domProps(
          ~href,
          ~className=active ? activeClassName : className,
          ~onClick,
          (),
        ),
      [|children|],
    );
  };
};

module Link = {
  let make =
      (~asTag="a", ~href, ~className="", ~activeClassName="active", children) =>
    ReasonReactCompat.wrapReactForReasonReact(
      Link3.make,
      Link3.makeProps(
        ~asTag,
        ~href,
        ~className,
        ~activeClassName,
        ~children=React.null,
        (),
      ),
      children,
    );
};