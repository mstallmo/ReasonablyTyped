open Belt;

type fileType =
  | CSS
  | FlowDefinition
  | GraphQL
  | Reason
  | Typed
  | TypeScriptDefintion;

type file = {
  type_: fileType,
  name: string,
  source: string,
};

let compile = (file, target) => {
  let typedModules =
    switch (file.type_) {
    | FlowDefinition => ParseFlow.parse(~name=file.name, ~source=file.source)
    | _ => raise(Errors2.Unimplemented)
    };

  Array.map(typedModules, typedMod =>
    switch (target) {
    | FlowDefinition => GenerateFlow.compile(typedMod)
    | Reason => GenerateReason.compile(typedMod)
    | _ => raise(Errors2.Unimplemented)
    }
  );
};
