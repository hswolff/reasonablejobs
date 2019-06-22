module Content = {
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

module Link = {
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