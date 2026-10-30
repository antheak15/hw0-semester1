#include <stdio.h>
#include<stdlib.h> /* Χρησιμοποιησα αυτήν την βιβλιοθήκη για μπορεί ο compiler να αναγνωρίσει την εντολή exit  και να τερματιστεί το πρόγραμμα αν υπάρχει σφάλμα */
/* Η πιο κάτω συνάρτηση υπολογίζει το άθροισμα των γνήσιων διαιρέτων ενός αριθμού*/
long long full_sequence (long long num){
    long long sum,i,temp;
    sum=1; /* Το αρχικοποιώ με 1 αφού το 1 είναι πάντα διαιρέτης κάθε αριθμού μεγαλύτερου του 1*/

    if(num<=1){
        return 0;
    } /* το 1 δεν έχει γνήσιους διαιρέτες */


    for(i=2;i*i<=num;i++){ /* εδώ βρίσκω τα ζευγάρια των διαιρέτων ενόσ αριθμού ώστε η διαδικασία εύρεσησ τουσ να είναι πιο γρήγορη*/
        if(num%i==0){      /* επίσησ στην συνθήκη του for ελέγχω μέχρι την ρίζα του αριθμού μου */
            temp=num/i;
            sum+=i;
            if(i!=temp){ /* εδώ ελέγχω αν το ζευγάρι του διαιρέτη είναι το ίδιο ώστε να μην ξαναπροσθεθεί*/
                sum+=temp;
            }
        }
        if(num>1000000000000000){ /* όταν ο αριθμός γίνει υπερβολικά μεγάλος το πρόγραμμα τερματίζεται με κωδικό εξόδου 1*/
        fprintf(stderr,"Number exceeds maximun supported integer(1000000000000000). Stopping.\n");
        exit(1);
        }

    }
    return sum; /*επιστρέφει στην main το άθροισμα των διαιρέτων ενός αριθμού */

}

/* Στην πιο κάτω συνάρτηση υπολογίζω το μήκος της aliquot, δηλαδή πόσες φορές χρειάζεται να βρω το αθροισμα των διαιρέτων ενός αριθμούυ μέχρι να φτάσει στο 0 ή να εξαντληθεί το όριο που έδωσε ο χρήστης*/
long long lengthf(long long num,long long maxl){
    long long counter=0;
    if(maxl==0){ /* αν ο χρήστης δώσει maxl==0 τότε δεν υπάρχει όριο */
        while(num!=0){
        num=full_sequence(num);
        counter++;
        }
    }
    else {
       while((maxl>0)&&(num!=0)){
            num=full_sequence(num); /* χρησιμοποιώντας την συνάρτηση full_sequence υπολογίζουμε το αθροισμα του επόμενου όρου κάθε φορά */
            counter++; /* και εδώ μετράμε τα βήματα (φορές) που χρειάστηκε */
            maxl--;
        }
    }
    return counter; /* επιστρέφεται το μήκος τησ ακολουθίας */
}

int main(void)
{
    long long sum,t2;
    long long maxl;
    char answer,t3;
    double t1;
    printf("Please give the number to start the aliquot sequence from: "); /* ζητήται ακέραιοσ */
    if(scanf("%lf",&t1)!=1){ /* εδώ η συνθήκη ελέγχει αν δώθηκε αριθμός, αν όχι το πρόγραμμα τερματίζεται */
        printf("Invalid input.\n");
        exit(1);
    }
   if(t1!=(long long)t1){ /*έλεγχος αν ο αριθμός που δόθηκε πιο πάνω είναι ακέραιος ή δεκαδικός , αν είναι δεκαδικός το πρόγραμμα τερματίεται */
       printf("Invalid input.\n");
        exit(1);
        }
    long long num=(long long)t1; /*αν δοθηκε ακέραιοσ αποθηκεύεται σε μια νέα μεταβλητή ο αριθμόσ */
    if(num<=0){/* αν δεν δωθεί θετικός ακεραιος το πρόγραμμα τερματίζεται λόγω σφάλματος*/
        printf("Invalid input.\n");
        exit(1);
    }
    printf("Provide the max aliquot length to look for (0 for the unlimited) : ");
    t2=scanf("%lld",&maxl); /* ζητείται το όριο του μέγιστου μήκους ακολουθίασ ή 0 για απεριόριστο */
    if(t2!=1 || maxl<0){ /*αν δεν δόθηκε θετικός αριθμός ή αν δόθηκε κάτι αλλο εκτόσ απο αριθμό το πρόγραμμα τερματίζεται */
         printf("Invalid input.\n");
        fflush(stdout); /* αυτό διασφαλίζει οτι τα μηνύματα εμφανίζονται πριν τερματιστεί το πρόγραμμα*/
         exit(1); 
    }
    printf("Do you want to print the full sequence ('f') or just the length ('l') ?");
    t3=scanf(" %c", &answer); /* ζητείται αν ο χρήστης αναζητά μήκοσ ή άθροισμα (έβαλα κενό ώστε για να αγνοηθεί το newline)*/
    if((t3!=1)||((answer!='l')&&(answer!='f'))){ /* αν δεν δοθεί χαρακτήρασ ή δοθεί χαρακτήρας εκτόσ των l και f, το πρόγραμμα τερματίζεται */
        printf("Invalid input.\n");
        fflush(stdout);
        exit(1);
    }
        if(answer=='l'){
        printf("Length of aliquot sequence : %lld\n",lengthf(num,maxl));
        }

        else if (answer=='f'){
            sum=num; /* αρχικοποιώ μια νέα μεταβλητή έτσι ώστε το πρόγραμμα να είναι πιο ευανάγνωστο και να μην μπερδευτώ με τισ μετβλητέσ */
            printf("%lld\n",sum);
            if(maxl==0){ /* εδώ η διαδικασία γίνεται χωρίσ όριο ,μέχρι ο αριθμόσ (sum ) να φτάσει στο 0*/

            while(sum!=0){
                sum=full_sequence(num); /* μέχρι το sum που επιστρέφει η συνάρτηση δεν γινεται 0 η διαδικασία συνεχίζεται */
                printf("%lld\n",sum);
                num=sum;

            }

         }

    else { /* αν υπάρχει όριο βημάτων */
               do {
                   sum=full_sequence(sum);
                   printf("%lld\n",sum);
                    maxl--;
                }while((sum!=0)&&(maxl>0));
            }
    }
    
    return 0;
}
