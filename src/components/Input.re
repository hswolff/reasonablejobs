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