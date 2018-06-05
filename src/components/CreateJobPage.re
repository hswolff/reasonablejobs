type state = {title: string};

type action =
  | Title(string)
  | None;

let component = ReasonReact.reducerComponent("CreateJobPage");

let str = ReasonReact.string;

let createJob = (_e, self: ReasonReact.self(state, _, _)) => {
    let job: JobData.job = {
      id: None,
      dateCreated: None,
      owner_id: Stitch.Client.authedId(API.getClient()),
      position: {
        title: self.state.title,
        location: "New York City",
        description: "Description of job",
        applyInstructions: "To apply do XYZ",
      },
      company: {
        name: "My Company Name",
        url: "http://cool.com",
        email: "my@email.com",
        description: "Such a description!",
      },
    };

    API.Job.create(~job) |> Js.Promise.then_((result) => {
      Js.log2("Created!", result);
      Js.Promise.resolve();
    }) |> ignore;
  };

let make = _children => {
  {
    ...component,
    initialState: () => {title: ""},
    reducer: (action, state: state) =>
      switch (action) {
      | Title(title) => ReasonReact.Update({...state, title})
      | None => ReasonReact.NoUpdate
      },
    render: self =>
      <UI.Content>
        <h1> (str("Create a Job")) </h1>
        <input
          value=self.state.title
          onChange=(
            event =>
              self.send(
                Title(
                  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
                ),
              )
          )
        />
        <button onClick=(self.handle(createJob))> (str("Create!")) </button>
      </UI.Content>,
  };
};