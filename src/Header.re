let component = ReasonReact.statelessComponent("Header");

let string = ReasonReact.string;

module Style = {
  open Css;
  let left = style([color(hex("444")), fontSize(px(68))]);
};

let make = _children => {
  ...component,
  render: _self =>
    <UI.Content tagName="header">
      <div className=Style.left> (string("Reasonable Jobs")) </div>
    </UI.Content>,
};