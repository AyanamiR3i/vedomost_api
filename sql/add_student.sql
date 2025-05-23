insert into students (name, lastname, patronymic, birthdate, fk_study_group, pol)
	values ($1, $2, $3, to_date($4, 'YYYY-MM-DD'), $5, $6);