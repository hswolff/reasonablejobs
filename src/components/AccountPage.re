type jobs = array(JobData.job);

type state = {jobs};

type action =
  | Data(jobs);

let component = ReasonReact.reducerComponent("AccountPage");

module Style = {
  open Css;
  let title =
    style([color(hex("444")), fontSize(px(28)), textAlign(center)]);
};

let make = _children => {
  let loadJobs = (_e, self: ReasonReact.self(state, _, _)) =>
    API.Job.get({"owner_id": Stitch.Client.authedId(API.getClient())}, jobs =>
      self.send(Data(jobs))
    );

  {
    ...component,
    initialState: () => {jobs: [||]},
    didMount: self => loadJobs((), self),
    reducer: (action, _state) =>
      switch (action) {
      | Data(jobs) => ReasonReact.Update({jobs: jobs})
      },
    render: self =>
      <UI.Content tagName="header">
        <div className=Style.title> (ReasonReact.string("Account")) </div>
        <div> (ReasonReact.string("Just the Jobs you have posted")) </div>
        <br />
        (
          self.state.jobs
          |> Array.mapi((index, job: JobData.job) =>
               <JobCell
                 key=(
                   switch (job.id) {
                   | Some(id) => id
                   | None => string_of_int(index)
                   }
                 )
                 job
                 onDeleted=(self.handle(loadJobs))
               />
             )
          |> ReasonReact.array
        )
      </UI.Content>,
  };
};