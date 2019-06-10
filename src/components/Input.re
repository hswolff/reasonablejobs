type state = {options: string};

type action =
  | Input(string);

let component = ReasonReact.reducerComponent("Input");

let make = _children => {
  ...component,
  initialState: () => {options: ""},
  reducer: (action, _state) =>
    switch (action) {
    | Input(nextValue) => ReasonReact.NoUpdate
    },
  render: self =>
    <div> (ReasonReact.string("hello" ++ self.state.options)) </div>,
};