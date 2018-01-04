# $1:type $2:output_file $3:start_index $4:max_index $5:increment
for((var = $3; var <= $4; var += $5)); do matmult_c.gcc $1 $var $var $var; done > $2