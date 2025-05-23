select s.pk as "pk", s.lastname as "lastname", s.name as "name", s.patronymic as "patronymic",
 s.pol as "gender", TO_CHAR(birthdate, 'YYYY-MM-DD') as "birthdate",
 g.name as "group" from students as s
 join groups as g on g.pk = s.fk_study_group;
