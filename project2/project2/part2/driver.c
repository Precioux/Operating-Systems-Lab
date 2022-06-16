#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include<linux/slab.h>                 //kmalloc()

/*Linked List Node*/
struct birthday{
	struct list_head list;     //linux kernel list implementation
	int day;
	int month;
	int year;
};
 
/*Declare and init the head node of the linked list*/
LIST_HEAD(Head_Node);
  
 
/*Module init Function*/
static int linkedlist_init(void)
{
        struct birthday *person1 = NULL;
        struct birthday *person2 = NULL;
        struct birthday *person3 = NULL;
        struct birthday *person4 = NULL;
        struct birthday *person5 = NULL;
 
        printk(KERN_INFO "making linked list..\n");
        
        /*Creating Node*/
        person1 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
        person2 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
        person3 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
        person4 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
        person5 = kmalloc(sizeof(struct birthday), GFP_KERNEL);
 
        /*Assgin the data that is received*/
        person1->day = 27;
	person1->month=2;
	person1->year=2021;

        person2->day = 27;
	person2->month=2;
	person2->year=2022;

        person3->day = 27;
	person3->month=2;
	person3->year=2023;

        person4->day = 27;
	person4->month=2;
	person4->year=2024;

        person5->day = 27;
	person5->month=2;
	person5->year=2025;
 
        /*Init the list within the struct*/
        INIT_LIST_HEAD(&person1->list);
 
        /*Add Node to Linked List*/
        list_add_tail(&person1->list, &Head_Node);

	/*Init the list within the struct*/
        INIT_LIST_HEAD(&person2->list);
 
        /*Add Node to Linked List*/
        list_add_tail(&person2->list, &Head_Node);

        /*Init the list within the struct*/
        INIT_LIST_HEAD(&person3->list);
 
        /*Add Node to Linked List*/
        list_add_tail(&person3->list, &Head_Node);

	/*Init the list within the struct*/
        INIT_LIST_HEAD(&person4->list);
 
        /*Add Node to Linked List*/
        list_add_tail(&person4->list, &Head_Node);

	/*Init the list within the struct*/
        INIT_LIST_HEAD(&person5->list);
 
        /*Add Node to Linked List*/
        list_add_tail(&person5->list, &Head_Node);

        struct birthday *temp;
        printk(KERN_INFO "linked list data\n");

        /*Traversing Linked List and Print its Members*/
        list_for_each_entry(temp, &Head_Node, list) {
            printk(KERN_INFO "This person will be born at %d-%d-%d",temp->year,temp->month,temp->day);
        }

 
	return 0;
}
 
/*
** Module Exit function
*/ 
static void linkedlist_exit(void)
{
	
	 printk(KERN_INFO "All data cleared and removed successflly!");
 
        /* Go through the list and free the memory. */
        struct birthday *cursor, *temp;
        list_for_each_entry_safe(cursor, temp, &Head_Node, list) {
            list_del(&cursor->list);
            kfree(cursor);
        }
       
}
 
module_init(linkedlist_init);
module_exit(linkedlist_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("samin mahdipor");
MODULE_DESCRIPTION("Kernel Linked List");
MODULE_VERSION("1");
