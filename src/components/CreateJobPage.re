let str = ReasonReact.string;

type state = {
  position: JobData.job_position,
  company: JobData.job_company,
};

type action =
  | U_Position_Title(string)
  | U_Position_Location(string)
  | U_Position_Description(string)
  | U_Position_ApplyInstructions(string)
  | U_Company_Name(string)
  | U_Company_Url(string)
  | U_Company_Email(string)
  | U_Company_Description(string)
  | SubmitForm
  | ResetForm;

let component = ReasonReact.reducerComponent("CreateJobPage");

let createJob = ({ReasonReact.state, send}) => {
  let job: JobData.job = {
    id: None,
    dateCreated: None,
    owner_id: Stitch.Client.authedId(API.getClient()),
    position: state.position,
    company: state.company,
  };

  API.Job.create(~job)
  |> Js.Promise.then_(result => {
       Js.log2("Created!", result);
       send(ResetForm);
       Js.Promise.resolve();
     })
  |> ignore;
};

let getFormValue = e => ReactEvent.Form.target(e)##value;

let getInitialState = () => {
  position: {
    title: "",
    location: "",
    description: "",
    applyInstructions: "",
  },
  company: {
    name: "",
    url: "",
    email: "",
    description: "",
  },
};

let make = _children => {
  ...component,
  initialState: () => getInitialState(),
  reducer: (action, state: state) =>
    switch (action) {
    | SubmitForm => ReasonReact.SideEffects(createJob)
    | ResetForm => ReasonReact.Update(getInitialState())
    | U_Position_Title(title) =>
      ReasonReact.Update({
        ...state,
        position: {
          ...state.position,
          title,
        },
      })
    | U_Position_Location(location) =>
      ReasonReact.Update({
        ...state,
        position: {
          ...state.position,
          location,
        },
      })
    | U_Position_Description(description) =>
      ReasonReact.Update({
        ...state,
        position: {
          ...state.position,
          description,
        },
      })
    | U_Position_ApplyInstructions(applyInstructions) =>
      ReasonReact.Update({
        ...state,
        position: {
          ...state.position,
          applyInstructions,
        },
      })
    | U_Company_Name(name) =>
      ReasonReact.Update({
        ...state,
        company: {
          ...state.company,
          name,
        },
      })
    | U_Company_Url(url) =>
      ReasonReact.Update({
        ...state,
        company: {
          ...state.company,
          url,
        },
      })
    | U_Company_Email(email) =>
      ReasonReact.Update({
        ...state,
        company: {
          ...state.company,
          email,
        },
      })
    | U_Company_Description(description) =>
      ReasonReact.Update({
        ...state,
        company: {
          ...state.company,
          description,
        },
      })
    },
  render: self =>
    <UI.Content>
      <h1> {str("Create a Job")} </h1>
      <br />
      <h2> {str("Position")} </h2>
      <Input />
      <input
        value={self.state.position.title}
        placeholder="Title"
        onChange={e => self.send(U_Position_Title(getFormValue(e)))}
      />
      <input
        value={self.state.position.location}
        placeholder="Location"
        onChange={e => self.send(U_Position_Location(getFormValue(e)))}
      />
      <input
        value={self.state.position.description}
        placeholder="Description"
        onChange={e => self.send(U_Position_Description(getFormValue(e)))}
      />
      <input
        value={self.state.position.applyInstructions}
        placeholder="Apply Instructions"
        onChange={e =>
          self.send(U_Position_ApplyInstructions(getFormValue(e)))
        }
      />
      <br />
      <h2> {str("Company")} </h2>
      <input
        value={self.state.company.name}
        placeholder="Name"
        onChange={e => self.send(U_Company_Name(getFormValue(e)))}
      />
      <input
        value={self.state.company.url}
        placeholder="Url"
        onChange={e => self.send(U_Company_Url(getFormValue(e)))}
      />
      <input
        value={self.state.company.email}
        placeholder="Email"
        onChange={e => self.send(U_Company_Email(getFormValue(e)))}
      />
      <input
        value={self.state.company.description}
        placeholder="Description"
        onChange={e => self.send(U_Company_Description(getFormValue(e)))}
      />
      <br />
      <button onClick={_e => self.send(SubmitForm)}>
        {str("Create!")}
      </button>
    </UI.Content>,
};