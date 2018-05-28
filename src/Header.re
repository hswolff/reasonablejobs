let component = ReasonReact.statelessComponent("Header");

let string = ReasonReact.string;

module Style = {
  let left = ReactDOMRe.Style.make(~color="#444444", ~fontSize="68px", ());
};

let make = _children => {
  ...component,
  render: _self =>
    <UI.Content tagName="header">
      <div style=Style.left> (string("Reasonable Jobs")) </div>
    </UI.Content>,
};