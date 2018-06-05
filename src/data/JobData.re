type job_position = {
  title: string,
  location: string,
  description: string,
  applyInstructions: string,
};

type job_company = {
  name: string,
  url: string,
  email: string,
  description: string,
};

type job = {
  id: option(string),
  owner_id: string,
  dateCreated: option(string),
  position: job_position,
  company: job_company,
};

module Encode = {
  let position = position =>
    Json.Encode.(
      object_([
        ("title", position.title |> string),
        ("location", position.location |> string),
        ("description", position.description |> string),
        ("applyInstructions", position.applyInstructions |> string),
      ])
    );

  let company = company =>
    Json.Encode.(
      object_([
        ("name", company.name |> string),
        ("url", company.url |> string),
        ("email", company.email |> string),
        ("description", company.description |> string),
      ])
    );

  let job = (job: job) =>
    Json.Encode.(
      object_([
        ("owner_id", job.owner_id |> string),
        ("position", job.position |> position),
        ("company", job.company |> company),
      ])
    );
};

module Decode = {
  let position = json =>
    Json.Decode.{
      title: json |> field("title", string),
      location: json |> field("location", string),
      description: json |> field("description", string),
      applyInstructions: json |> field("applyInstructions", string),
    };

  let company = json =>
    Json.Decode.{
      name: json |> field("name", string),
      url: json |> field("url", string),
      email: json |> field("email", string),
      description: json |> field("description", string),
    };

  let job = json =>
    Json.Decode.{
      id:
        json |> field("_id", map(val_ => val_, optional(Stitch.toString))),
      dateCreated:
        switch (json |> field("dateCreated", optional(string))) {
        | exception (DecodeError(v)) => Some(v)
        | v => v
        },
      owner_id: json |> field("owner_id", string),
      company: json |> field("company", company),
      position: json |> field("position", position),
    };

  let jobs = json => json |> Json.Decode.array(job);
};