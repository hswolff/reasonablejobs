type homepageJobs = array(JobData.job);

module Style = {
  open Css;
  let title =
    style([color(hex("444")), fontSize(px(28)), textAlign(center)]);
};

[@react.component]
let make = _ => {
  let (jobs, setJobs) = React.useState(_ => [||]);

  let loadJobs = () => API.Job.getAll(jobs => setJobs(_ => jobs));

  React.useEffect0(_ => {
    loadJobs();
    None;
  });

  <UI.Content tagName="header">
    <div className=Style.title> {ReasonReact.string("Home Page")} </div>
    {jobs
     |> Array.mapi((index, job: JobData.job) =>
          <JobCell
            key={
              switch (job.id) {
              | Some(id) => id
              | None => string_of_int(index)
              }
            }
            job
            onDeleted=loadJobs
          />
        )
     |> ReasonReact.array}
  </UI.Content>;
};