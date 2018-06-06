let component = ReasonReact.statelessComponent("JobCell");

let string = ReasonReact.string;

module Style = {
  let container =
    Css.(
      style([
        display(flexBox),
        justifyContent(spaceBetween),
        border(px(1), solid, black),
        padding(px(10)),
        borderRadius(px(4)),
      ])
    );
};

let make = (~job: JobData.job, ~onDeleted: unit => unit, _children) => {
  let delete = _e =>
    switch (job.id) {
    | Some(id) =>
      API.Job.delete(~id, ~callback=_result => onDeleted()) |> ignore
    | None => Js.log("No id exists to delete")
    };

  {
    ...component,
    render: _self =>
      <div className=Style.container>
        <div className="left"> (string(job.position.title)) </div>
        <div className="right">
          <button onClick=delete> (string("Delete")) </button>
        </div>
      </div>,
  };
};