1) This application is start from the ../inventory file, which mean after runserver you access the target application by, for example localhost:8000/inventory.
2)For the requirement of the drink/snack have a list of recommended snack/drink, in my view, the pair well drink/snack have to at inventory first.
Therefore, when we try to add drink or snack, we only can select the existed snacks/drink. And their relationship is many to many.
3)../inventory/views.py contain the backend method of this application:
   a)index() is the display all the drink/snacks in the inventory.
   b)delete() is delete the certain item
   c)edit()is GET method of the edit page
   d)editsomething() is POST method of the edit
   e)add() is GET method of the add page
   f)addsomething() is POST method of the add
   e)getdetails is the method, when we try to add drink/snacks,the good pair have to existed snacks/drink. Therefore,when we select
     type of food, we can view the selection in the mutiple select box. Something like we should select the country frist and we can
     view the city.

