describe('rentingItemsList', function() {
    // Load the module that contains the `rentingItemsList` component before each test
    beforeEach(module('rentalpropertyApp'));

    // Test the controller
    describe('RentingItemsListController', function() {
        it('should create a `rentingItems` model with 3 rentingItems', inject(function($componentController) {
            var ctrl = $componentController('rentingItemsList');
            expect(ctrl.rentingItems.length).toBe(3);
        }));
    });
});