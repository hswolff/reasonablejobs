type job_position = {
  id: int,
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
  dateCreated: int,
  position: job_position,
  company: job_company,
};