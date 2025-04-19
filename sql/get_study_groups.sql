select g.*,
(select count(*) from students as s where s.fk_study_group = g.pk) as "students_amount"
from groups as g
