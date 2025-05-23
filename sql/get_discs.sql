select d.pk as "pk", d.disc_name as "name", d.hours_amount  as "hoursAmount", a.attest_type as "attestationType" 
 from discipline as d
 join attestation as a on a.pk = d.fk_attestation
 order by "name";