#! /bin/bash

for f in *.c ; do
	echo $f
	
	cat > 12-bits/12-$f  <<EOF
//
// -----------------
//

#define BITS_IN_JSAMPLE 12
#include "../$f"

EOF
	
	cat > 16-bits/16-$f  <<EOF
//
// -----------------
//

#define BITS_IN_JSAMPLE 16
#include "../$f"

EOF

done