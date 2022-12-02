The general design will be as follows
 - Big struct holding containers of all possible component
 - this struct also remembers which ids exist, which do not
 - all containers have a map from a global Entity id, to a local one
