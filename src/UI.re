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