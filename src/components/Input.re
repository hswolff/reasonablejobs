[@bs.config {jsx: 3}];

[@react.component]
let make = (~name) => {
  let (count, setCount) = React.useState(() => 0);

  <div>
    {ReasonReact.string("hello" ++ name ++ string_of_int(count))}
    <button onClick={_ => setCount(_ => count + 1)}>
      {React.string("Click me")}
    </button>
  </div>;
};

module Jsx2 = {
  let component = ReasonReact.statelessComponent("Image");
  /* `children` is not labelled, as it is a regular parameter in version 2 of JSX */
  let make = (~name, children) =>
    ReasonReactCompat.wrapReactForReasonReact(
      make,
      makeProps(~name, ()),
      children,
    );
};