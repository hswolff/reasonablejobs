module Content = {
  let container =
    Css.(
      style([
        margin2(~v=px(0), ~h=auto),
        width(px(Config.Styles.contentWidth)),
      ])
    );

  let component = ReasonReact.statelessComponent("Content");

  let make = (~tagName="div", children: array(ReasonReact.reactElement)) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        tagName,
        ~props={"className": container},
        children,
      ),
  };
};

module Link = {
  let component = ReasonReact.statelessComponent("Link");
  let make = (~asTag="a", ~href, children) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        asTag,
        ~props={
          "href": href,
          "onClick": e => {
            ReactEventRe.Mouse.preventDefault(e);
            ReasonReact.Router.push(href);
          },
        },
        children,
      ),
  };
};