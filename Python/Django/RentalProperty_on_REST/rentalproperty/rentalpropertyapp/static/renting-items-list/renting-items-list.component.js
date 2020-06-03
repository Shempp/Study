'use strict';

// Register `rentingItemsList` component on the 'rentingItemsList' module
angular.
    module('rentingItemsList').
    component('rentingItemsList', {  // This name is what AngularJS uses to match to the `<renting-items-list>` element.
        // Note: The URL is relative to our `home.html` file
        templateUrl: '/static/renting-items-list/renting-items-list.template.html',
        controller: function RentingItemsListController() {
            var currentDate = new Date();
            this.rentingItems = [
                {
                    name: 'Saint-Petersburg, st. Begovaya, 10',
                    price: '25000',
                    pub_date: currentDate,
                }, {
                    name: 'Saint-Petersburg, st. Begovaya, 11',
                    price: '20000',
                    pub_date: currentDate,
                }, {
                    name: 'Saint-Petersburg, st. Begovaya, 12',
                    price: '15000',
                    pub_date: currentDate,
                }
            ];
        }
    });