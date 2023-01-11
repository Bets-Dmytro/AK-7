#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
//#include <asm-generic/bug.h>

MODULE_AUTHOR("Bets Dmytro");
MODULE_DESCRIPTION("Lab 6");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int number_of_iterations = 1;

module_param(number_of_iterations, uint, S_IRUGO);
MODULE_PARM_DESC(num_of_greet, "How much times 'Hello, World!' will be printed");

struct list_of_proccess 
{
	struct list_head list;
	ktime_t proccess_time;
};

static struct list_head proccess_list_head;
static LIST_HEAD(proccess_list_head);

void next_proccess(void) 
{
	struct list_of_proccess *proccess = NULL;
	proccess = kmalloc(sizeof(struct list_of_proccess), GFP_KERNEL);
	proccess->proccess_time = ktime_get();
	list_add_tail(&proccess->list, &proccess_list_head);
}

static int __init hello_init(void)
{
	if (number_of_iterations == 0 || (number_of_iterations >= 5 && number_of_iterations <= 10)) 
		printk(KERN_WARNING "Number equals 0 or is between 5 and 10");  

	BUG_ON(number_of_iterations > 10);
  
	int i;
	for (i = 0; i < number_of_iterations; i++) 
	{
		if (number_of_iterations == 6)
			BUG();
        	printk(KERN_EMERG "Hello, World!\n");
        	next_proccess();
	}
	return 0;
}

static void __exit hello_exit(void) 
{
	struct list_of_proccess *md, *tmp;
	list_for_each_entry_safe(md, tmp, &proccess_list_head, list) 
	{
		printk(KERN_EMERG "Proccess time is %lld\n", md->proccess_time);
		list_del(&md->list);
		kfree(md);
  	}
}

module_init(hello_init);
module_exit(hello_exit);

