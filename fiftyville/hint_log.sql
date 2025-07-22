.output resultado.txt
.schema crime_scene_reports


.output resultado.txt
SELECT description
FROM crime_scene_reports
WHERE street like "%Humphrey%";
