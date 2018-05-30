let component = ReasonReact.statelessComponent("Header");

let string = ReasonReact.string;

module Style = {
  open Css;
  let title =
    style([color(hex("444")), fontSize(px(68)), textAlign(center)]);
  let nav =
    style([
      textAlign(center),
      selector(" a", [margin2(~v=px(0), ~h=px(20))]),
      selector(" a.active", [color(black), textDecoration(none)]),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <UI.Content tagName="header">
      <div className=Style.title> (string("Reasonable Jobs")) </div>
      <nav className=Style.nav>
        <UI.Link href="/"> (ReasonReact.string("Home")) </UI.Link>
        <UI.Link href="/about"> (ReasonReact.string("About")) </UI.Link>
      </nav>
    </UI.Content>,
};