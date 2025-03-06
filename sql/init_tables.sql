create table groups(
pk serial primary key,
name varchar(128) not null,
semester int not null);

create table attestation(
pk serial primary key,
attest_type varchar(64) not null);

create table discipline(
pk serial primary key,
disc_name varchar(128) not null,
hours_amount int,
fk_attestation int references attestation (pk) not null);

create table students(
pk serial primary key,
lastname varchar(128) not null,
name varchar(128) not null,
patronymic varchar(128),
birthdate date,
fk_study_group int references groups (pk) not null,
pol varchar(4) not null);

create table vedomost(
pk serial primary key,
year_for int not null,
semester int not null,
fk_descipline int references discipline (pk),
fk_student int references students (pk),
mark int,
balls int,
date_created date default current_date);

alter table vedomost
add constraint check_semester
check(semester in (0, 1));
