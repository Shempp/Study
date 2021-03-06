'use strict';

// Register `rentingItemsList` component on the 'rentingItemsList' module
angular.
    module('rentingItemsList').
    component('rentingItemsList', {  // This name is what AngularJS uses to match to the `<renting-items-list>` element.
        // Note: The URL is relative to our `home.html` file
        templateUrl: '/static/renting-items-list/renting-items-list.template.html',
        controller: ['$http', '$location', function RentingItemsListController($http, $location) {
                var self = this;
                var itemsURL = 'http://127.0.0.1:8000/api/rentingitems/';
                var logoutURL = 'http://127.0.0.1:8000/rentalpropertyapp/logout';

                // TODO: going back should not overwrite data
                self.newPrice = '';
                self.newAddress = '';
                self.orderProp = 'price';

                // REST HTTP GET
                $http.get(itemsURL).then(function(response) {
                    self.rentingItems = response.data;
                });

                // Register callback addNewRentingItem for adding new RentingItem
                self.addNewRentingItem = function() {
                    $http.post(itemsURL, {
                        'address': self.newAddress,
                        'price': parseInt(self.newPrice)
                    }, {withCredentials: true}).then(function(response) {
                        self.rentingItems.push(response.data);
                    });

                    // Refreshing model on home page after adding new item
                    self.newPrice = '';
                    self.newAddress = '';
                    self.orderProp = 'price';
                };

                // Register callback logout for logging out
                self.logout = function() {
                    $http.post(logoutURL, {}).then(function(response) {
                        // Redirect to login page
                        //$location.url(loginURL);
                    });
                };


                /*
                // Make http request to server to fetch the data in json file
                // For tests (from file)
                $http.get('/static/RentingItems.json').then(function(response) {
                    self.rentingItems = response.data;
                });
                 */

                /*
                // For tests (dummy data)
                var currentDate = new Date();
                this.rentingItems = [
                    {
                        address: 'Saint-Petersburg, st. Begovaya, 10',
                        price: '25000',
                        pub_date: currentDate,
                    }, {
                        address: 'Saint-Petersburg, st. Begovaya, 11',
                        price: '20000',
                        pub_date: currentDate,
                    }, {
                        address: 'Saint-Petersburg, st. Begovaya, 12',
                        price: '15000',
                        pub_date: currentDate,
                    } , {
                        address: 'Anapa, st. Pushkina, 1',
                        price: '9000',
                        pub_date: currentDate,
                    }
                ];
                this.orderProp = 'price';
                 */
        }]
    });