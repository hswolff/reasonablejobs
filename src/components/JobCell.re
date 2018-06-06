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
        margin2(~v=px(20), ~h=auto),
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

  let isOwner = job.owner_id == Stitch.Client.authedId(API.getClient());
  {
    ...component,
    render: _self =>
      <div className=Style.container>
        <div className="left"> (string(job.position.title)) </div>
        <div className="right">
          (
            isOwner ?
              <button onClick=delete> (string("Delete")) </button> :
              ReasonReact.null
          )
        </div>
      </div>,
  };
};