insert into groups (name, semester)
values ($1, $2)
returning pk, name, semester;