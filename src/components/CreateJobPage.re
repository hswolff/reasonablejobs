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
  | ResetForm;

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

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state: state, action) =>
        switch (action) {
        | ResetForm => getInitialState()
        | U_Position_Title(title) => {
            ...state,
            position: {
              ...state.position,
              title,
            },
          }
        | U_Position_Location(location) => {
            ...state,
            position: {
              ...state.position,
              location,
            },
          }
        | U_Position_Description(description) => {
            ...state,
            position: {
              ...state.position,
              description,
            },
          }
        | U_Position_ApplyInstructions(applyInstructions) => {
            ...state,
            position: {
              ...state.position,
              applyInstructions,
            },
          }
        | U_Company_Name(name) => {
            ...state,
            company: {
              ...state.company,
              name,
            },
          }
        | U_Company_Url(url) => {
            ...state,
            company: {
              ...state.company,
              url,
            },
          }
        | U_Company_Email(email) => {
            ...state,
            company: {
              ...state.company,
              email,
            },
          }
        | U_Company_Description(description) => {
            ...state,
            company: {
              ...state.company,
              description,
            },
          }
        },
      getInitialState(),
    );

  let createJob = _ => {
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
         dispatch(ResetForm);
         Js.Promise.resolve();
       })
    |> ignore;
  };

  <UI.Content>
    <h1> {str("Create a Job")} </h1>
    <br />
    <h2> {str("Position")} </h2>
    <Input name="Ok" />
    <input
      value={state.position.title}
      placeholder="Title"
      onChange={e => dispatch(U_Position_Title(getFormValue(e)))}
    />
    <input
      value={state.position.location}
      placeholder="Location"
      onChange={e => dispatch(U_Position_Location(getFormValue(e)))}
    />
    <input
      value={state.position.description}
      placeholder="Description"
      onChange={e => dispatch(U_Position_Description(getFormValue(e)))}
    />
    <input
      value={state.position.applyInstructions}
      placeholder="Apply Instructions"
      onChange={e =>
        dispatch(U_Position_ApplyInstructions(getFormValue(e)))
      }
    />
    <br />
    <h2> {str("Company")} </h2>
    <input
      value={state.company.name}
      placeholder="Name"
      onChange={e => dispatch(U_Company_Name(getFormValue(e)))}
    />
    <input
      value={state.company.url}
      placeholder="Url"
      onChange={e => dispatch(U_Company_Url(getFormValue(e)))}
    />
    <input
      value={state.company.email}
      placeholder="Email"
      onChange={e => dispatch(U_Company_Email(getFormValue(e)))}
    />
    <input
      value={state.company.description}
      placeholder="Description"
      onChange={e => dispatch(U_Company_Description(getFormValue(e)))}
    />
    <br />
    <button onClick={_ => createJob()}> {str("Create!")} </button>
  </UI.Content>;
};