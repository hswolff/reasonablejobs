let component = ReasonReact.statelessComponent("HomePage");

module Style = {
  open Css;
  let title =
    style([color(hex("444")), fontSize(px(28)), textAlign(center)]);
};

let make = _children => {
  ...component,
  render: _self =>
    <UI.Content tagName="header">
      <div className=Style.title> (ReasonReact.string("Home Page")) </div>
      <JobCell title="Job 1" />
      <br />
      <JobCell title="Job 2" />
    </UI.Content>,
};