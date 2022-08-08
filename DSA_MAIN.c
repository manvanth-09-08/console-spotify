///Required header files

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#include<unistd.h>

///Doubly linked list structure

struct spotify
{
    char song_name[50],song_artist[50],movie_name[50],language[50],genre[50];
    int year_of_release,like,times_played;
    float duration, rating;
    struct spotify *next;
    struct spotify *prev;
};

///Structure for sorting

typedef struct
{
    char song_name1[50],song_artist1[50],movie_name1[50];
    float duration1, rating1;
    int position;
}SPOTIFY;

typedef struct spotify *NODE;

///Global Declaration

NODE head=NULL;
NODE root=NULL;
int deleted_elements=1;
int global_count;
int inorder_count=0;
FILE *fp=NULL;
char cur_playlist[50];

///Function to load song from file to double linked list
///Initially song from SONGS.txt will be loaded
///Also to play from specific playlist the same function is executed
///Arguments passed are the name of the playlist that has to be (SONGS.txt initially)
///Returns a doubly circular linked list and the number of nodes

void load_song(char playlist_name[50])
{
    ///Initialisation of global variables

    global_count=0;
    head=NULL;

    ///Opens the required file

    FILE *fp=fopen(playlist_name,"r");

    ///Check if the playlist with playlist_name exists

    if(fp==NULL)
    {
        printf("No such playlist exist Please check the speling and cases\n");
        return;
    }

    ///If playlist exists copy the playlist name to cur_playlist
    ///This is useful to write into file

    strcpy(cur_playlist,playlist_name);

    ///Load into doubly circular linked list
    while(!feof(fp))
    {
        ///Global count is to keep track of total number of nodes

         global_count++;

         ///Create new node

        NODE newn=malloc(sizeof(struct spotify)),cur=head;

        ///Read from the file and copy it in circular doubly linked list

        fscanf(fp,"%s %s %s %s %s %d %d %d %f %f\n",newn->song_name,newn->song_artist,newn->movie_name,newn->language,newn->genre,&newn->year_of_release,&newn->like,&newn->times_played,&newn->duration,&newn->rating);

        ///Insert at end of circular doubly linked list
        if(head==NULL)
        {
            head=newn;
            head->next=head;
            head->prev=head;
        }
        else
        {
            while(cur->next!=head)
                cur=cur->next;
            newn->prev=cur;
            cur->next=newn;
            newn->next=head;
            head->prev=newn;
        }

    }

    ///File close

    fclose(fp);
}

///Function to write into the file
///This function does the work of updating the file
///This function writes into the file name stored in cur_playlist
///It takes cur_playlist from global variable
///Returns updated file

void write_into_file()
{
    FILE *fp=fopen(cur_playlist,"w");

    ///Checks weather the file is opened

    if(fp==NULL)
    {
        printf("Cannot open file\n");
        return;
    }

    ///Initialising of cur pointer to head

    NODE cur=head;

    ///Traversing until head is reached and writing it into the file

    do
    {
        fprintf(fp,"%s %s %s %s %s %d %d %d %0.2f %0.2f\n",cur->song_name,cur->song_artist,cur->movie_name,cur->language,cur->genre,cur->year_of_release,cur->like,cur->times_played,cur->duration,cur->rating);
        cur=cur->next;

    }while(cur!=head);

    ///file close

    fclose(fp);

}


///Function to generate link to share the song
///It uses a simple hash function to generate link
///The ascii value of ith index is multiplied by 11^(i/2)
///11^(i/2) because 11^i gives a large value which cannot be stored in int
///Arguments passed is the name of the song which needs to be shared
///Returns a pseudo link to that song


void generate_link(char name[50])
{
    int c=0;

    ///Hashing function to generate link

    for(int i=0;name[i]!='\0';i++)
        c+=name[i]*pow(11,i/2);

        ///Displays link and waits for the user to continue

     printf("https://open.spotify.com/id=%d\n",c);
     printf("Copy this link and share it to your friends\n");
     printf("Press enter to continue\n");
}


///Function to search a song by its name
///This Function uses string compare operation
///It starts from head and until the head is reached it compares the song name and plays the particular song
///Arguments passed is the name of the song
///There is no such case like the the song doesn't play because the song name is already searched in search_through_bruteforce function
///Here it just helps to find the address of the song
///Returns the adress of the song to play_music()

int search_by_song(char name[50])
{
    int i=0;

    ///Initialisation of cur pointer to head

    NODE cur=head;

    ///Run the loop until the song with song name is found
    do
    {
        ///if song name is matched return the value of i

        if(!strcmp(cur->song_name,name))
        {
            return i;
        }

        ///else increment i by 1 and move to next node and compare
        i++;
        cur=cur->next;

    }while(cur!=head);          ///Stopping condition

}


///Function to search a song by its movie_name
///This Function uses string compare operation
///It starts from head and until the head is reached it compares the song name and plays the particular song
///Arguments passed is the movie name
///This function displays the song of a particular movie and asks the user to input the song's index
///Returns the index of the song to play_music()


int search_by_movie(char name[50])
{
    ///Initialisation of i and current pointer

    int i=0;
    NODE cur=head;

    ///Run the loop until head is reached and display all the songs with movie name given by the user

    do
    {
        ///If the movie name is matched display the name of the song along with its index

        if(!strcmp(cur->movie_name,name))
        {
            printf("%d %s\n",i,cur->song_name);
        }

        ///Increment i and current and go to loop

        i++;
        cur=cur->next;

    }while(cur!=head);          ///Stopping condition


    ///Asks to enter the index of the song to be played to user

    printf("enter the choice\n");
    scanf("%d",&i);

    ///Returns the index value to search_through_bruteforce function through which it goes to play_music and plays the specific song

    return i;

}


///Function to search a song by its artist_name
///This Function uses string compare operation
///It starts from head and until the head is reached it compares the song name and plays the particular song
///Arguments passed is the artist name
///This function displays the songs of a particular artist and asks the user to input the song's index
///Returns the index of the song to play_music()



int search_by_artist(char name[50])
{

    ///Initialisation of i and current pointer

    int i=0;
    NODE cur=head;

    do
    {

        ///If the movie name is matched display the name of the song along with its index

        if(!strcmp(cur->song_artist,name))
        {
            ///If the artist name is matched display the name of the song along with its index

            printf("%d %s\n",i,cur->song_name);

        }

         ///Increment i and current and go to loop

        i++;
        cur=cur->next;

    }while(cur!=head);              ///Stopping condition

    ///Asks to enter the index of the song to be played to user

    printf("enter the choice\n");
    scanf("%d",&i);

     ///Returns the index value to search_through_bruteforce function through which it goes to play_music and plays the specific song

    return i;

}


///Function to search the song through brute force algorithm
///Here the function takes letter by letter input from the user until the user enteres 0
///It searches through brute force method and displays song name, movie name, artist name separately
///Song and album are the variable to keep track of indices of searched song and searched movies
///Input is the group of letters to be searched
///Output is the song name, movie name, artist name and index


int search_through_brute_force()
{

    ///Clear the screen  and change the console colour

    system("cls");
    system("color B0");

    ///Declaration and initialisation of variables

    int j,i,song=0,album=0,k=0;
    NODE cur=head;
    char s[50],c;
    char matched[100][50];


    ///Instruction to the user

    printf("Please enter letter by letter\n");
    printf("Press 0 to exit the search and play from searched song\n");
  S:printf("Search here\n");

  getchar();

  ///Take input from the user

    scanf("%c",&c);
    s[0]=c;
    s[1]='\0';

    ///Start from head and search until the head is reached

    do
    {
        ///Initialise k and take the string length of the pattern

        k=0;
        int n=strlen(s);

        ///Brute force algorithm to search the song name

        do
        {

            ///Initialise varibales

            int m=strlen(cur->song_name),flag=1;

            ///Brute force search

            for(i=0;i<=m-n;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(cur->song_name[i+j]!=s[j])
                        break;

                }

                ///If the string is matched search if it has already occurred

                if(j==n)
                {
                    for(j=0;j<k;j++)
                    {
                        if(!strcmp(matched[j],cur->song_name))
                        {
                            flag=0;
                            break;
                        }
                    }

                    ///If the searched string has not occurred copy it to the matched array

                    if(flag)
                    {
                        strcpy(matched[k++],cur->song_name);
                    }

                }

            }

            cur=cur->next;

        }while(cur!=head);

        ///Copy the index of matched array to song

        song=k;

        ///If any song is searched display it

        if(k)
        {
            printf("\nSongs\n");
            for(i=0;i<k;i++)
                printf("%d %s\n",i,matched[i]);
        }

        ///Else display message saying no song is found

        else
        {
            printf("No songs found\n");
        }

       ///Brute force algorithm to search the movie name

         do
        {

              ///Initialise varibales

            int m=strlen(cur->movie_name),flag=1;

             ///Brute force search

            for(i=0;i<=m-n;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(cur->movie_name[i+j]!=s[j])
                        break;

                }

                ///If the string is matched, search if it has already occurred

                if(j==n)
                {
                    for(j=song;j<k;j++)
                    {
                        if(!strcmp(matched[j],cur->movie_name))
                        {
                            flag=0;
                            break;
                        }
                    }


                     ///If the searched string is not occurred copy it to the matched array

                    if(flag)
                    {
                        strcpy(matched[k++],cur->movie_name);
                    }

                }

            }

            cur=cur->next;

        }while(cur!=head);

         ///If any movie is searched display it

        if(k-song)
        {
            printf("\nMovie\n");\

            for(i=song;i<k;i++)
            {
                printf("%d %s\n",i,matched[i]);
            }

             ///Copy the index of matched array to album

            album=k;
        }

        else
        {
                printf("No Movie name found\n");

        }

         do
        {

            ///Initialise varibales

            int m=strlen(cur->song_artist),flag=1;

             ///Brute force search

            for(i=0;i<=m-n;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(cur->song_artist[i+j]!=s[j])
                        break;

                }

                 ///If the string is matched, search if it is already occurred

                if(j==n)
                {
                    for(j=album;j<k;j++)
                    {
                        if(!strcmp(matched[j],cur->song_artist))
                        {
                            flag=0;
                            break;
                        }
                    }


                     ///If the searched string has not occurred copy it to the matched array

                    if(flag)
                    {
                        strcpy(matched[k++],cur->song_artist);
                    }

                }

            }

            cur=cur->next;

        }while(cur!=head);

         ///If any artist is searched display it

        if(album-k)
        {
            printf("\nArtist\n");
            for(i=album;i<k;i++)
            {
                printf("%d %s\n",i,matched[i]);
            }

        }

        else
        {
                printf("No Artist found please search again\n");
               printf("Press 0 to return\n");
               printf("Press 1 to search again\n");
               scanf("%d",&i);
               if(i)
                goto S;
               else
                return -1;
        }

        ///Take next letter input from the user

        getchar();
        scanf("%c",&c);

        ///Join that letter to the string s

        s[strlen(s)]=c;
        s[strlen(s)+1]='\0';

    }while(c!='0');

    ///Enter the index value

    SEARCH: printf("enter the number\n");
            scanf("%d",&i);

            ///Conditions to call the correct function

            if(i<song)
            {
                k=search_by_song(matched[i]);
            }

            else if(i>=song && i<=album)
            {
                k=search_by_movie(matched[i]);
            }

            else if(i>song && i<=k)
            {
                k=search_by_artist(matched[i]);
            }

            else
            {
                printf("invalid choice\n");
                goto SEARCH;
            }

            ///Return the index value to play_music()

            return k;

}


///Function to search song in specific playlist
///This function takes playlist name from the user
///Search is done using the same brute force algorithm
///Returns the index to play_music()

int search_in_specific_playlist()
{
    ///Declaration of variables

    char playlist_name[50],name[50],filename[50];
    int i;

    ///Asks user to input playlist name

    printf("enter the playlist in which song should be searched\n");
    scanf("%s",playlist_name);

    ///Writes the current playlist into file inorder to store the updated data

    write_into_file();

    ///Copies the playlist name to filename from playlist_name

     sprintf(filename,"%s.txt",playlist_name);

     ///Loads the songs from user defined playlist into circular doubly linked list

    load_song(filename);

    ///Search operation is carried out using brute force algorithm

    i=search_through_brute_force();

    ///Returns the index of required song

    return i;

}


///Menu function to display the various functions

void menu()
{
    ///Change the colour of console

   system("color CF");

    printf("\n\n\n\n\n\n");

    printf("\t\t\t\t\tEnter your choice\n\n");
    printf("\t\t\t0. Exit playing song and return to main menu\n");
    printf("\t\t\t1. Play next song\n");
    printf("\t\t\t2. Play previous song\n");
    printf("\t\t\t3. Like song\n");
    printf("\t\t\t4. Add to playlist\n");
    printf("\t\t\t5. Search song\n");
    printf("\t\t\t6. Sort\n");
    printf("\t\t\t7. Play song from recommendations\n");
    printf("\t\t\t8. Play shuffle songs\n");
    printf("\t\t\t10. Show queue\n");
    printf("\t\t\t11. Display music details\n");
    printf("\t\t\t12. Show liked songs\n");
    printf("\t\t\t13. Share song\n");
    printf("\t\t\t14. Search in specific playlist\n");
    printf("\t\t\t15. Display music from same language\n");
    printf("\t\t\t16. Display music from same genre\n");

}


///Function to display the current playing song
///Arguments passed are the current time, name of the song, total duration of the song
///Displays all of the arguments passed in low graphical interface


void music_interface(float cur,char name[20],float dur)
{
    ///Declaration of variables
    int n=strlen(name),i;

    ///Graphical user interface

    printf("\n\n\n\n\n");
    printf("\t\t");
    system("color 20");

    ///For loop until the total duration is reached

    for( i=0;i<80;i++)
    {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
        printf(" ");

    }

    printf("\n");

    for(int j=0;j<8;j++)
    {
        printf("\t\t");
        printf(" ");
        for(i=0;i<78;i++)
        {
            printf(" ");
        }

        printf(" \n");

    }

    printf("\t\t");

    printf(" ");

    for(i=0;i<((79-n)/2);i++)
    {
        printf(" ");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    printf("%s",name);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);

    for(i=0;i<((78-n)/2);i++)
    {
        printf(" ");
    }

    printf(" \n");

    printf("\t\t");

    printf(" ");

    for(i=0;i<(66/2);i++)
     {
         printf(" ");
     }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    printf("%0.2f of %0.2f",cur,dur);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);

    for(i=0;i<(66/2);i++)
    {
        printf(" ");
    }

    printf(" \n");

    for(int j=0;j<8;j++)
    {
        printf("\t\t");

        printf(" ");

        for(i = 0;i < 78;i++)
        {
             printf(" ");
        }

        printf(" \n");
    }



    printf("\t\t");

    for(int i=0;i<80;i++)
    {
        printf(" ");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|BACKGROUND_RED|48);

    printf("\n\n\n\n\n\n\t\t\t\t\tPress any key to display the menu\n");

}

///This function does the work of shuffle play
///Uses random function and generates random variable and plays music
///Arguments : none
///Plays random music


void shuffle_play()
{

    ///srand to generate random function every time

    srand(time(0));

    ///global_count is the total number of nodes

    int i=rand()%global_count;

    NODE cur=head;

    ///For loop runs i times

    for(;i>=0;i--)
    {
        cur=cur->next;
    }

        ///Plays music
        i=0;
   LOOP: for(;i<cur->duration;i+=0.01)

        {
            system("cls");
            music_interface(i,cur->song_name,cur->duration);
            sleep(1);

            ///Code snippet to increment after 60 secs are over

            int x=i;
            x=x*100;
            if((int)(i*100-x)==59)
            {
                i+=0.4;
                goto LOOP;
            }

            ///Stop the loop if user pressed enter

            if(kbhit())
            {
                ///Display the menu

                printf("Press 1 to play next song\n");
                printf("Press 2 to play from normal queue\n");
                printf("Press 3 to exit the application");

                int hit;
                scanf("%d",&hit);


                switch(hit)

                {
                    case 1 :shuffle_play();

                    case 2:return;

                    case 3: exit(0);
                }
            }

        }


}

///Function to add current playing song to particular playlist
///If playlist does not exist
///Arguments passed is the name of the song
///Writes the current playing  song into required playlist


void add_to_playlist(char name_of_the_song[20])
{
    ///Declaration of variables

    int n;
    char playlist_name[50],filename[50];
    NODE cur=head;

    ///Clear screen and change console colour

    system("cls");
    system("color E5");

    ///Asks the user to enter the playlist name

    printf("\n\n\n\n\n\n");
    printf("\t\t\t");
    printf("Enter the play list name to which song needs to be added\n");
    scanf("%s",playlist_name);

    ///Copies the name from play_list name to filename adding .txt

    sprintf(filename,"%s.txt",playlist_name);

    ///Opens file in read mode just to check if the file exists

    fp=fopen(filename,"r");

    ///If playlist does not exists asks user to create new playlist

    if(fp==NULL)

    {
        printf("Playlist does not exist\n");
        printf("Do want to create new playlist?\n");
        printf("Press 1 to create new playlist\n");
        printf("Press 2 to enter another name\n");
        printf("Press 3 to return\n");
        scanf("%d",&n);

        ///Switch case to create or retry

        switch(n)
        {
            ///To create a new playlist/file

            case 1:fp=fopen(filename,"w");
                    ///Run the loop until the name of the song is reached

                    while(strcmp(cur->song_name,name_of_the_song))
                    {
                        cur=cur->next;
                    }

                     ///Write into file the song details

                    fprintf(fp,"%s %s %s %s %s %d %d %d %0.2f %0.2f\n",cur->song_name,cur->song_artist,cur->movie_name,cur->language,cur->genre,cur->year_of_release,cur->like,cur->times_played,cur->duration,cur->rating);

                    printf("Playlist created and song added successfully\n");
                    break;

            ///Retry the name of the playlist
            case 2:add_to_playlist(name_of_the_song);

            break;

            ///Return back

            case 3:return;

        }


    }

    ///If the playlist exists append the current song into the existing playlist

    else
    {
        fp=fopen(filename,"a");

        while(strcmp(cur->song_name,name_of_the_song))
        {
            cur=cur->next;
        }

         ///Write into the playlist

        fprintf(fp,"s=%s %s %s %s %s %d %d %d %0.2f %0.2f\n",cur->song_name,cur->song_artist,cur->movie_name,cur->language,cur->genre,cur->year_of_release,cur->like,cur->times_played,cur->duration,cur->rating);
    }

}


///This is the function to copy the circular doubly linked list into array of structure to sort using heap sort


int copy(SPOTIFY s[],int k)
{
    NODE cur=head;

     ///Loop runs until all data of linked list is copied  in array

    do
    {
        ///Copying the every element which is present in linked list to array
        ///Since year of release and like does not contribute to sorting it is not copied

       strcpy(s[k].song_name1,cur->song_name);
       strcpy(s[k].song_artist1,cur->song_artist);
       strcpy(s[k].movie_name1,cur->movie_name);
       s[k].duration1=cur->duration;
       s[k].rating1=cur->rating;

        k++;

        cur=cur->next;
    }while(cur!=head);

    ///Return total number of nodes

    return k;



}


///This function sorts the array
///Partitions into halves and sorts it accordingly

void merg_in_array(SPOTIFY a[],int l,int mid,int h)
{

    int i=l,j,k=l;
   SPOTIFY c[300];
    j=mid+1;
    while(i<=mid&&j<=h)
    {
        if(a[i].duration1<a[j].duration1)
        {
            c[k++]=a[i++];

        }
        else
        {
            c[k++]=a[j++];

        }
    }


    for(;i<=mid;i++)
    {

       c[k++]=a[i];

    }
    for(;j<=h;j++)
    {
      c[k++]= a[j];
    }

    for(i=l;i<=h;i++)
    {
      a[i] =c[i];

    }

}


///This function creates partition and sorts it using merge sort
///Arguments passed are the copied array and total number of nodes
///Returns sorted array

void merge_sort(SPOTIFY a[],int n)
{
    int k,l,h,mid,i;
    for(k=2;k<=n;k=k*2)
    {

        for(i=0;i+k-1<n;i=i+k)
        {
            l=i;
            h=i+k-1;
            int mid=(l+h)/2;
            merg_in_array(a,l,mid,h);
        }
    }

    if(n%2!=0)
   {

     merg_in_array(a,0,k/2-1,n-1);

   }

}


///This function helps in the sorting alphabetically using BST
///Here instead of creating the new structure we have taken existing structure
///prev pointer is taken as left and next pointer is taken as right
///Arguments passed is the address of node need to be inserted
///Return BST

void insert_tree(NODE cur)
{
    ///Creating new node to insert get data of present node  in it

    NODE newn=malloc(sizeof(struct spotify));

    ///Checks if memory is allocated and node is created

    if(newn==NULL)
     {
         printf("Memory not allocated\n");
         return;
     }

      ///Copying the whole data present in node of doubly linked list into newly created node

    strcpy(newn->song_name,cur->song_name);
    strcpy(newn->song_name,cur->song_name);
    strcpy(newn->movie_name,cur->movie_name);
    strcpy(newn->song_artist,cur->song_artist);
    strcpy(newn->language,cur->language);
    strcpy(newn->genre,cur->genre);
    newn->duration=cur->duration;
    newn->like=cur->like;
    newn->rating=cur->rating;
    newn->times_played=cur->times_played;
    newn->year_of_release=cur->year_of_release;
    newn->prev=NULL;
    newn->next=NULL;

    NODE temp=root;
    NODE tail=NULL;

    ///Check if root is present

    if (root==NULL)
    {
        ///If root is not present assign the newly created node to root

       root=newn;
    }

    ///If root is present connect newn to left or right of leaf node

    else
    {
         ///Create array  and copy the  song name which we want to insert in tree in  that array

       char temp1[50];
       strcpy(temp1,cur->song_name);

       ///Get first word of the song_name

       char key=temp1[0];

       ///Run the loop until leaf node is reached

       while(temp)
       {
        ///Tail pointer to keep point of leaf node

        tail=temp;

        /// copy the  song name to be inserted in temp2

        char temp2[50];
        strcpy(temp2,temp->song_name);

         ///Get first word of the song_name

        char t2=temp2[0];
         if(t2>key)
         {
             /// If key's ascii  value is less move temp pointer to left side

             temp=temp->prev;

         }
         else
         {
             ///Else move the temp pointer to right side

            temp=temp->next;

         }

       }

       ///Loop will end when temp pointer becomes null
       ///Tail pointer will be pointing the leaf node
       ///Insert newn to tail

       char temp2[50];
       strcpy(temp2,tail->song_name);

       char x=temp2[0];
       if(x>key)
       {

         tail->prev=newn;

       }

       else
       {

          tail->next=newn;

       }


    }

    ///Return BST


}

///Copy from tree takes address from inorder() and creates an array of structure which helps to play from sorted list

void copy_from_tree(SPOTIFY s[],int k,NODE cur)
{
        strcpy(s[k].song_name1,cur->song_name);
       strcpy(s[k].song_artist1,cur->song_artist);
       strcpy(s[k].movie_name1,cur->movie_name);
       s[k].duration1=cur->duration;
       s[k].rating1=cur->rating;
}


///This function functions inorder traversal of the BST
///It gives sorted order


void inorder(NODE cur,SPOTIFY s[])
{
    /// Pass the root value to in order function from main
    /// This is recursive function
    /// The previous pointer left node in tree
    /// The next pointer right node in tree
    /// In order will print in sorted alphabetical order
   if(cur)
   {
       inorder(cur->prev,s);
       printf("%s\n",cur->song_name);

       ///inorder_count helps in copying to the array

       inorder_count++;
       copy_from_tree(s,inorder_count,cur);

      inorder(cur->next,s);

   }



}


///This function helps in creating the heap based on rating
///Arguments passed are copied structure and index
///Returns heap


void insert_rating(SPOTIFY s[],int n)
{
     ///Copy the element in temp you want to sort

    float temp=s[n].rating1;

     ///Copy the whole structure in the stemp

    SPOTIFY stemp=s[n];
    int i=n;

    ///Loop runs until index is greater than 1 and getting first largest element in the array

    while(i>1 && temp>s[i/2].rating1)
    {
        s[i]=s[i/2];
        i=i/2;
    }

     ///Inserting the element in the position where i is pointing

    s[i]=stemp;
}


void createheap(SPOTIFY s[],int c)
{

        ///Running loop for i=2 to number of elements in array
        ///No need to run from 1 because one element will automatically  get it position


            for(int i=2;i<c;i++)
            {

                insert_rating(s,i);

            }

}


///This function is based on root deletion method
///Every time the element has to be deleted it needs to be swapped with the last node and hence it gets its position

void delete_heap(SPOTIFY s[],int c)
{
     SPOTIFY temp=s[1];

      /// deleted_elements  variable helps us to  get the count of number of  deleted elements

      ///Swap root and last node and delete the last node from heap

     s[1]=s[c-deleted_elements];
     s[c-deleted_elements]=temp;

     ///Increment deleted_elements

      deleted_elements++;

       ///After every deletion we have to create the heap for rest of the elements except the last one

     createheap(s,(c-deleted_elements));

}

///Sorts in ascending order of duration or rating whichever is applicable
///Displays sorted list


void heap_sort(SPOTIFY s[],int n)
{

    ///Run the loop until all the elements are sorted

    for(int i=1;i<n-1;i++)
    {

        delete_heap(s,n);

    }

    ///Clear the screen

    system("cls");

    ///Display sorted list

    for(int i=1;i<n;i++)
    {

        printf("%s \n",s[i].song_name1);

    }

}

///This function plays the music from sorted list
///It only works for sort by duration and rating
///Arguments passed is the copied structure
///Displays current playing song


void play(SPOTIFY s[],int k,int start)
{
    int i=start,choice;
    float j;
    do
    {

    ///Runs loop from 1 to total number of copied nodes

    INIT:for(;i<=k;i++)
        {
            j=0;
        LOOP:for(;j<s[i].duration1;j+=0.01)
            {

                sleep(1);
                system("cls");
                int x=j;
                x=x*100;
                if((int)(i*100-x)==59){
                        i+=0.4;
                    goto LOOP;}
                NODE cur2=NULL;
                music_interface(j,s[i].song_name1,s[i].duration1);

                ///Runs until user press enter
                ///If user press enter ,the following menu is displayed and the respective functionalities is carried out


                if(kbhit())
                {
                    printf("enter 0 to stop\n");
                    printf("Enter 1 to play next song\n");
                    printf("Enter 2 to play previous song\n");
                    scanf("%d",&choice);
                    switch(choice)
                    {

                        case 0:return;

                        case 1:i++;
                        if(i==k-(!start))
                        {
                            i=1;
                        }
                        goto INIT;

                        case 2: i--;
                                if(i==start-1)
                                {
                                    i=k-(!start);
                                }
                        goto INIT;

                    }

                }


            }

        }

    }while(1);

}

///This function displays the recommended songs and asks the user to play
///Recommendations are done if the songs are from same artist or from same movie
///Asks user to play songs from recommendation or return
///Arguments passed are the name of the artist and movie name
///Returns list of song

void recommendations(char current_artist_name[20],char current_movie_name[20])
{
    NODE cur=head;
    int i=0,n,k=1;
    SPOTIFY s[300];

    system("color F0");

    ///Run the loop from head to head

    do
    {
        ///If song is found with same artist name or movie name it is copied into structure

        if(!strcmp(current_artist_name,cur->song_artist)|| !strcmp(current_movie_name,cur->movie_name))
        {
            strcpy(s[k].song_name1,cur->song_name);
            strcmp(s[k].movie_name1,cur->movie_name);
            strcmp(s[k].song_artist1,cur->song_artist);
            s[k].duration1=cur->duration;
            s[k].rating1=cur->rating;
            s[k].position=i;
            k++;
        }

        i++;
        cur=cur->next;

    }while(cur!=head);

    ///Sorting is done based on rating

    createheap(s,k);
    heap_sort(s,k);

    ///Asks user to play the song

    printf("Press 1 to play songs\n");
    printf("Press 0 to return\n");
    scanf("%d",&i);
    if(i==1)
    {
         play(s,k,1);
    }
    else
        return;


}


///Main function to sort
///Asks user which type of sort needs to be performed
///Returns sorted list

void sort()
{
    int choice,choice1,k;
    SPOTIFY s[300];

    ///Clears screen and changes console colour

    system("cls");
    system("color DF");

    ///Provides menu for the user

    printf("Please enter the choice\n");
    printf("1. Sort by duration\n");
    printf("2. Sort by rating\n");
    printf("3. Sort by alphabets\n");


    scanf("%d",&choice);

    if(choice == 1)
    {
        k=copy(s,0);
         merge_sort(s,k);

        for(int i=0;i<k;i++)
       {

           printf("%s \n",s[i].song_name1);

       }

    }

    else if(choice==2)
    {
        k=copy(s,1);
        createheap(s,k);
        heap_sort(s,k);
    }

    else if(choice==3)
    {
        NODE cur=head;
        do
        {
            insert_tree(cur);
            cur=cur->next;

        }while(cur!=head);

        printf("\n\n");
        inorder(root,s);
    }


    ///Asks user if play the sorted list

    printf("Do you want to play the sorted list?\n");
    printf("Press 1 to play\n");
    printf("Press 0 to go back\n");
    scanf("%d",&choice1);

    if(choice1==1)
    {
        if(choice==1)
        {
           play(s,global_count,0);
        }
        else
        {
            play(s,global_count,1);
        }

    }

    else
    {
        return;
    }

}


///This functions displays the liked songs
///There is a structure element named like which is assigned 0 initially but when its liked it changes to 1
///Returns the list of liked songs


void liked_songs()

{
    ///Declaration of variable

    NODE cur=head;

    system("cls");

    ///Run the loop from head to head

    do
    {
       if(cur->like==1)
       {
            printf("%s %s\n",cur->song_name,cur->movie_name);
       }

       cur=cur->next;

    }while(cur!=head);

    getchar();
    getchar();

}

///Share song function returns a link
///It uses a variant of hash function
///Arguments passed is the current address of node
///Returns a link

void share_song(NODE cur)
{
    ///Clears the screen

    system("cls");

    ///Declaration of variable

    int choice;

    ///Asks user to enter the choice
    printf("Enter your choice\n");
    printf("1. To share the current song\n");
    printf("2. To share the album\n");
    scanf("%d",&choice);

    ///Sends the required data into required function

    if(choice==1)
        generate_link(cur->song_name);
    else
        generate_link(cur->movie_name);

    ///Does not return unless enter is pressed
    getchar();
    getchar();

}

///Function displays the details of the current playing song

void song_details(NODE cur)
{
    ///Clears the screen and changes console colour

    system("cls");
    system("color E0");

    ///Displays music details

    printf("Name = %s\n",cur->song_name);
    printf("Movie = %s\n",cur->movie_name);
    printf("Artist = %s\n",cur->song_artist);
    printf("Language = %s\n",cur->language);
    printf("Genre = %s\n",cur->genre);
    printf("Year of release = %d\n",cur->year_of_release);
    printf("Overall rating = %0.2f\n",cur->rating);
    printf("Press enter to continue\n");


    ///Waits until user presses enter

    getchar();
    getchar();

}

 ///This function displays the music from same language
 ///Arguments passed is the language
 ///Returns songs from same langauge
void display_language(char language[50])
{
    NODE cur=head;
    do
    {
        if(!strcmp(cur->language,language))
        {
            printf("%s\n",cur->song_name);
        }
    }while(cur!=head);
    getchar();
    getchar();
}


///This function displays the music from same genre
 ///Arguments passed is the genre
 ///Returns songs from same genre

void display_genre(char genre[50])
{
    NODE cur=head;
    do
    {
        if(!strcmp(cur->genre,genre))
        {
            printf("%s\n",cur->song_name);
        }
    }while(cur!=head);
}

///Most important function after int main()
///All the functionalities are controlled by this function

void play_music()
{
    ///Declaration of variables
    NODE cur=head;
    int hit;
    float i=0;
    char temp[50];

    ///Run the loop from head to head

    do
    {
       INITIAL : i=0;

       ///Play music
       ///Run the loop from 0 to duration of the song

        LOOP: for(;i<cur->duration;i+=0.01)
        {
            system("cls");

            ///To jump into next value after completion of 60 secs

            int x=i;
            x=x*100;
            if((int)(i*100-x)==59)
            {
                    i+=0.4;
                goto LOOP;
            }

            ///Play music

            NODE cur2=NULL;
            music_interface(i,cur->song_name,cur->duration);
            sleep(1);

            ///Increment number of times played by 1 if he hears a song for more than half of the duration

            if(i==cur->duration/2)
            {
                cur->times_played++;
                write_into_file();
                load_song("SONGS.txt");
            }


            ///Run the loop until user presses enter in keyboard

            if(kbhit())
            {
                ///If enter is pressed display the menu and take input from the user

                system("cls");
                menu();

                int k;

                 scanf("%d",&hit);

                 ///Switch case of hit

                 switch(hit)
                 {
                     case 0: return;

                     ///Play next song

                     case 1: cur=cur->next;
                     goto INITIAL;

                     ///Play previous song

                     case 2: cur=cur->prev;
                     goto INITIAL;

                     ///Like the song

                     case 3: cur->like=1;
                     write_into_file();
                     load_song("SONGS.txt");
                     break;

                     ///Add to playlist

                     case 4:add_to_playlist(cur->song_name);
                     break;

                     ///Search song from the current playlist

                     case 5:k=search_through_brute_force();
                            cur=head;
                            for(int j=0;j<k;j++)
                                cur=cur->next;
                            goto INITIAL;
                     break;

                     ///Sort the current playlist

                    case 6:sort();
                     break;

                     ///Play recommended songs

                     case 7:  recommendations(cur->song_artist,cur->movie_name);
                           break;

                    ///Shuffle the queue

                    case 8:shuffle_play();
                            return;

                    ///Display queue

                    case 10: cur2=cur;
                    system("cls");

                            do
                            {
                                printf("%s %s %s %0.2f %0.2f \n",cur2->song_name,cur2->song_artist,cur2->movie_name,cur2->duration,cur->rating);
                                cur2=cur2->next;
                            }while(cur2!=cur);
                            getchar();
                            getchar();
                            break;

                    ///Display song details

                    case 11:song_details(cur);
                            break;

                    ///Display liked songs

                    case 12 : liked_songs();
                    break;

                    ///Share current song or album

                    case 13: share_song(cur);
                    break;

                    ///Search the song in specific playlist

                    case 14: search_in_specific_playlist();
                    break;

                    case 15:printf("Enter the language First letter caps\n");
                        scanf("%s",temp);
                        display_language(temp);
                        break;

                    case 16:printf("Enter the genre First letter caps\n");
                        scanf("%s",temp);
                        display_genre(temp);
                        break;

                    default: printf("Invalid choice\n");


                 }
            }

        }

    }while(1);

    return;

}

///Function helps to play the song from specific playlist
///Input is the playlist name
///Reads from playlist and creates a circular doubly linked list
///Plays from particular paylist


void play_from_play_list()
{
    ///Declaration of variables
    char playlist_name[50];
    int n;

    ///Asks to enter playlist name from the user

    printf("Enter the playlist name to be played\n");
    scanf("%s",playlist_name);

    ///Copies the playlist name by adding .txt

    sprintf(playlist_name,"%s.txt",playlist_name);

    ///Checks if the playlist exists

    fp=fopen(playlist_name,"r");

    ///Prompts if playlist does not exits

    if(fp==NULL)
    {
        printf("No playlist with such name exists\n");
        printf("Please check the spelling\n");
        printf("Press 1 to retry\n");
        printf("Press 2 to go back\n");
        scanf("%d",&n);

        if(n==1)
        {
            play_from_play_list();
        }

        else
        {
            return;
        }

    }

    ///Writes the current playlist into the file to retain updation

    write_into_file();

    ///Create circular doubly linked list

    SAME_PLAYLIST :  load_song(playlist_name);

    ///Play from current file

    play_music();


    printf("Do you want to play from another playlist?\n");
    printf("Press 1 to play different playlist\n");
    printf("Press 2 to play same playlist\n");
    printf("Press 3 to return to main song menu\n");
    scanf("%d",&n);

    ///Menu

    switch(n)
    {
        ///Play from different playlist

        case 1:play_from_play_list();
        break;

        ///Play from same playlist

        case 2: goto SAME_PLAYLIST;

        ///Play from songs

        case 3: write_into_file();
            load_song("SONGS.txt");
            return;
    }

}



///Gives the disclaimer page


void disclaimer()
{
    system("color B4");
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t     ");
    printf("This is just a mock application\n\n");
    printf("\t\t\tPlease plug in earphone to your mobile and enjoy your music\n\n");
    printf("\t\t\tThe best part of this spotify is you don't get annoying ads\n\n");
    printf("\t\t\t    ");
    printf("U can just see the timer and the song being played\n\n");
    printf("\t\t\t\t\tPlease imagine the song\n\n");
    printf("\t\t\tBy pressing enter u agree to all our terms and conditions\n\n");
    printf("\t\t\tTerms and conditions are nothing but the above points\n\n\n");
    printf("\t\t\t                    ");
    printf("Happy listening!!!!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),432);
    printf("\n\n\nPress enter to agree and continue\n");

    getchar();
}

///Main function

int main()
{
    ///Declaration of variables
    int n;

    ///Opens the file
    fp=fopen("SONGS.txt","a");

    ///If file not found

    if(fp==NULL)
    {
        printf("file not found");
    }

     ///Creates doubly circular linked list

    load_song("SONGS.txt");

    ///Displays welcome page

   
    //welcome_page();

    ///After the user presses enter clears the screen

    system("cls");

    ///Displays disclaimer

    disclaimer();

    ///Runs the loop until the user presses 3
    while(1)
    {

        ///Displays menu clears the screen and changes the console colour

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
        system("cls");

        for(int i=0;i<8;i++)
        {
            printf("\n");
        }

        system("color 80");
        printf("\t\t\t\t");
        printf("Press 1 to play normally              \n");
        printf("\t\t\t\t");
        printf("Press 2 to play from specific playlist\n");
        printf("\t\t\t\t");

        printf("Press 3 to exit                       \n");
        printf("\t\t\t\t");

        scanf("%d",&n);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
        if(n==1)
        {
            play_music();
        }

        else if(n==2)
        {
            play_from_play_list();
        }

        else
        {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);

            write_into_file();

            printf("Music playing stopped\n");
            fclose(fp);

            return 0;
        }

    }

}
