﻿using kayito_Editor.Source;
using System;
using System.Data;
using System.Data.OleDb;
using System.Windows.Forms;

namespace kayito_Editor.Forms
{

	public partial class ServerStats : Form
	{
		public ServerStats()
		{
			InitializeComponent();
		}

		private void ServerStats_Load(object sender, EventArgs e)
		{
			if (Import.Me_Connection.State != ConnectionState.Open)
			{
				MessageBox.Show($"No connection.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

				this.Dispose();
			}

			string query = null;

			try
			{
				this.Cursor = Cursors.WaitCursor;

				query = $"SELECT COUNT(1) FROM MEMB_INFO";

				OleDbDataReader reader = new OleDbCommand(query, Import.Me_Connection).ExecuteReader();

				if (reader.Read())
				{
					this.Accounts_Cant.Text = string.Format("{0}", reader.GetValue(0));
				}

				reader.Close();

				query = $"SELECT COUNT(1) FROM MEMB_STAT WHERE ConnectStat = 1";

				reader = new OleDbCommand(query, Import.Me_Connection).ExecuteReader();

				if (reader.Read())
				{
					this.Onlines_Cant.Text = string.Format("{0}", reader.GetValue(0));
				}

				reader.Close();

				query = $"SELECT COUNT(*) from Character";

				int TotalChar = 0;

				reader = new OleDbCommand(query, Import.Mu_Connection).ExecuteReader();

				if (reader.Read())
				{
					TotalChar = reader.GetInt32(0);

					this.Characters_Cant.Text = string.Format("{0}", TotalChar);
				}

				reader.Close();

				query = $"SELECT Class, COUNT(Class) as Cant from Character group by Class order by Class asc";

				reader = new OleDbCommand(query, Import.Mu_Connection).ExecuteReader();

				while (reader.Read())
				{
					int Class = reader.GetByte(0);

					ListViewItem lista = new ListViewItem(Import.Classes.ContainsKey(Class) ? Import.Classes[Class] : Import.Classes[-1]);

					int ClassCant = reader.GetInt32(1);

					lista.SubItems.Add(string.Format("{0:00}% ({1})", (ClassCant * 100 / TotalChar), ClassCant));

					this.Characters_List.Items.Add(lista);
				}

				reader.Close();
			}
			catch (Exception exception)
			{
				MessageBox.Show($"[SQL] {query}\n[Error] {exception.Message}\n[Source] {exception.Source}\n[Trace] {exception.StackTrace}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
			}

			this.Cursor = Cursors.Default;
		}
	}
}