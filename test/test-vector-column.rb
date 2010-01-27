# Copyright (C) 2010  Kouhei Sutou <kou@clear-code.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License version 2.1 as published by the Free Software Foundation.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

class VectorColumnTest < Test::Unit::TestCase
  include GroongaTestUtils

  def setup
    setup_database
    setup_tables
  end

  def setup_tables
    Groonga::Schema.define do |schema|
      schema.create_table("Users",
                          :type => :hash,
                          :key_type => "UInt32") do |table|
      end

      schema.create_table("Communities",
                          :type => :hash,
                          :key_type => "ShortText") do |table|
        table.reference("users", "Users", :type => :vector)
      end
    end

    @users = Groonga::Context.default["Users"]
    @communities = Groonga::Context.default["Communities"]
  end

  def test_set_and_get
    groonga = @communities.add("groonga")
    morita = @users.add(29)
    groonga["users"] = [morita]

    assert_equal([29], @users.collect {|record| record.key})
    assert_equal([29], groonga["users"].collect {|record| record.key})
  end
end
