module Content = {
  let component = ReasonReact.statelessComponent("Content");
  let make = (~tagName="div", children: array(ReasonReact.reactElement)) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        tagName,
        ~props={
          "style":
            ReactDOMRe.Style.make(
              ~width=Config.Styles.contentWidthAsString,
              ~margin="0 auto",
              (),
            ),
        },
        children,
      ),
  };
};