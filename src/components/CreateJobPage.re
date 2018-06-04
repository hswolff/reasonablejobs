type state = {formData: option(string)};

type action =
  | None;

let component = ReasonReact.reducerComponent("CreateJobPage");

let make = _children => {
  ...component,
  initialState: () => {formData: None},
  reducer: (action, state: state) =>
    switch (action) {
    | None => ReasonReact.NoUpdate
    },
  render: self =>
    <UI.Content>
      <h1> (ReasonReact.string("Create a Job")) </h1>
    </UI.Content>,
};