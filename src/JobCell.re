let component = ReasonReact.statelessComponent("JobCell");

let string = ReasonReact.string;

module Style = {
  open Css;
  let container =
    style([
      border(px(1), solid, black),
      padding(px(10)),
      borderRadius(px(4)),
    ]);
};

let make = (~title, _children) => {
  ...component,
  render: _self => <div className=Style.container> (string(title)) </div>,
};