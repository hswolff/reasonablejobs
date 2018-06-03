type homepageJobs = list(JobData.test);

type state = {jobs: homepageJobs};

type action =
  | Data(homepageJobs);

let component = ReasonReact.reducerComponent("HomePage");

module Style = {
  open Css;
  let title =
    style([color(hex("444")), fontSize(px(28)), textAlign(center)]);
};

let make = _children => {
  ...component,
  initialState: () => {jobs: []},
  didMount: self => API.fetchJobs(jobs => self.send(Data(jobs))),
  reducer: (action, _state) =>
    switch (action) {
    | Data(jobs) => ReasonReact.Update({jobs: jobs})
    },
  render: self =>
    <UI.Content tagName="header">
      <div className=Style.title> (ReasonReact.string("Home Page")) </div>
      (
        self.state.jobs
        |> Belt.List.toArray
        |> Array.map((job: JobData.test) => <JobCell title=job.owner_id />)
        |> ReasonReact.array
      )
      <JobCell title="Job 1" />
      <br />
      <JobCell title="Job 2" />
    </UI.Content>,
};