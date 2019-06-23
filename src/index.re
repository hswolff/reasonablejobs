[%bs.raw {|require('./index.css')|}];

API.createStitchClient(() =>
  ReactDOMRe.renderToElementWithId(<App />, "root")
);