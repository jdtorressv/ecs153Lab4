# ecs153Lab4
Torres, Joseph, jdtorres@ucdavis.edu, 996202666
Al Rakabi, Zaid, zhalrakabi@ucdavis.edu, 913779745

Runpriv grants root permissions to a second program called sniff. It performs several checks to prevent security breaches. These include checking that the UID of the calling process matches that of the student who wrote sniff, validating the user's password over the UC DAVIS CAS, ensuring modifications to sniff are less than one minute old, and verifying that only the student has execute permissions on sniff.    

To compile, simply type 'make'. 


